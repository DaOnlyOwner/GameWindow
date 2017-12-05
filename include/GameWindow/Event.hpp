//
// Created by Jan_M720 on 14.10.2017.
//

#pragma once

#include <vector>
#include <memory>
#include "Delegate.hpp"
#include <algorithm>

namespace doo
{
	typedef unsigned int DelegateID;

	template <typename... TArgs>
	struct EventGuard
	{
		~EventGuard();
		EventGuard& operator=(const EventGuard& p_other) = delete;
		EventGuard& operator=(EventGuard&& p_other) noexcept;

		EventGuard(const EventGuard& p_other) = delete;
		EventGuard(EventGuard&& p_other) noexcept;

	private:
		template <typename... T>
		class Event;

		Event<TArgs...>* m_event;
		DelegateID m_del_id;
	};


	template <typename... TArgs>
	class Event
	{
	public:
		typedef Delegate<void (TArgs ...)> DelegateType;

		DelegateID Subscribe(DelegateType p_type)
		{
			delegate_helper helper;
			helper.delegate = std::move(p_type);
			helper.id = m_id_counter++;
			m_delegates.push_back(helper);
			return helper.id;
		}

		bool Unsubscribe(DelegateID p_id)
		{
			auto it = std::find_if(m_delegates.begin(), m_delegates.end(), [p_id](const delegate_helper& p_helper)
			{
				return p_helper.id == p_id;
			});
			if (it == m_delegates.end())
				return false;
			std::swap(*it, m_delegates.back());
			m_delegates.pop_back();
			return true;
		}

		EventGuard<TArgs...> CreateGuard(DelegateID p_id) const
		{
			return {&this, p_id};
		}

		void operator()(TArgs ... p_args) const
		{
			for (const delegate_helper& helper : m_delegates)
			{
				helper.delegate(p_args...);
			}
		}

	private:
		struct delegate_helper
		{
			DelegateType delegate;
			DelegateID id;
		};

	private:
		std::vector<delegate_helper> m_delegates;
		DelegateID m_id_counter = 0;
	};

	template <typename ... TArgs>
	EventGuard<TArgs...>::~EventGuard()
	{
		if (m_event != nullptr)
			m_event->Unsubscribe(m_del_id);
	}

	template <typename ... TArgs>
	EventGuard<TArgs...>& EventGuard<TArgs...>::operator=(EventGuard&& p_other) noexcept
	{
		if (&p_other != this)
		{
			m_event = p_other.m_event;
			m_del_id = p_other.m_del_id;
			m_event = nullptr;
		}
		return *this;
	}

	template <typename ... TArgs>
	EventGuard<TArgs...>::EventGuard(EventGuard&& p_other) noexcept: m_event(p_other.m_event), m_del_id(p_other.m_del_id)
	{
		p_other.m_event = nullptr;
	}
}
